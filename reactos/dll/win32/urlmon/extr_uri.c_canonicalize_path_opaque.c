#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ scheme_type; char* path; int path_len; scalar_t__ is_relative; scalar_t__ scheme; } ;
typedef  TYPE_1__ parse_data ;
typedef  char WCHAR ;
struct TYPE_8__ {int path_start; int path_len; int canon_len; char* canon_uri; } ;
typedef  TYPE_2__ Uri ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__ const*,TYPE_2__*,int,int,int /*<<< orphan*/ ,int) ; 
 int TRUE ; 
 scalar_t__ URL_SCHEME_FILE ; 
 scalar_t__ URL_SCHEME_JAVASCRIPT ; 
 scalar_t__ URL_SCHEME_MK ; 
 scalar_t__ URL_SCHEME_UNKNOWN ; 
 int Uri_CREATE_FILE_USE_DOS_PATH ; 
 int Uri_CREATE_NO_CANONICALIZE ; 
 int Uri_CREATE_NO_ENCODE_FORBIDDEN_CHARACTERS ; 
 int /*<<< orphan*/  debugstr_wn (char*,int) ; 
 char decode_pct_val (char const*) ; 
 scalar_t__ is_ascii (char const) ; 
 int /*<<< orphan*/  is_reserved (char const) ; 
 scalar_t__ is_unreserved (char const) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pct_encode_val (char const,char*) ; 
 int remove_dot_segments (char*,size_t) ; 

__attribute__((used)) static BOOL canonicalize_path_opaque(const parse_data *data, Uri *uri, DWORD flags, BOOL computeOnly) {
    const WCHAR *ptr;
    const BOOL known_scheme = data->scheme_type != URL_SCHEME_UNKNOWN;
    const BOOL is_file = data->scheme_type == URL_SCHEME_FILE;
    const BOOL is_mk = data->scheme_type == URL_SCHEME_MK;

    if(!data->path) {
        uri->path_start = -1;
        uri->path_len = 0;
        return TRUE;
    }

    uri->path_start = uri->canon_len;

    if(is_mk){
        /* hijack this flag for SCHEME_MK to tell the function when to start
         * converting slashes */
        flags |= Uri_CREATE_FILE_USE_DOS_PATH;
    }

    /* For javascript: URIs, simply copy path part without any canonicalization */
    if(data->scheme_type == URL_SCHEME_JAVASCRIPT) {
        if(!computeOnly)
            memcpy(uri->canon_uri+uri->canon_len, data->path, data->path_len*sizeof(WCHAR));
        uri->path_len = data->path_len;
        uri->canon_len += data->path_len;
        return TRUE;
    }

    /* Windows doesn't allow a "//" to appear after the scheme
     * of a URI, if it's an opaque URI.
     */
    if(data->scheme && *(data->path) == '/' && *(data->path+1) == '/') {
        /* So it inserts a "/." before the "//" if it exists. */
        if(!computeOnly) {
            uri->canon_uri[uri->canon_len] = '/';
            uri->canon_uri[uri->canon_len+1] = '.';
        }

        uri->canon_len += 2;
    }

    for(ptr = data->path; ptr < data->path+data->path_len; ++ptr) {
        BOOL do_default_action = TRUE;

        if(*ptr == '%' && known_scheme) {
            WCHAR val = decode_pct_val(ptr);

            if(is_unreserved(val)) {
                if(!computeOnly)
                    uri->canon_uri[uri->canon_len] = val;
                ++uri->canon_len;

                ptr += 2;
                continue;
            }
        } else if(*ptr == '/' && is_file && (flags & Uri_CREATE_FILE_USE_DOS_PATH)) {
            if(!computeOnly)
                uri->canon_uri[uri->canon_len] = '\\';
            ++uri->canon_len;
            do_default_action = FALSE;
        } else if(*ptr == '\\') {
            if((data->is_relative || is_mk || is_file) && !(flags & Uri_CREATE_FILE_USE_DOS_PATH)) {
                /* Convert to a '/'. */
                if(!computeOnly)
                    uri->canon_uri[uri->canon_len] = '/';
                ++uri->canon_len;
                do_default_action = FALSE;
            }
        } else if(is_mk && *ptr == ':' && ptr + 1 < data->path + data->path_len && *(ptr + 1) == ':') {
            flags &= ~Uri_CREATE_FILE_USE_DOS_PATH;
        } else if(known_scheme && is_ascii(*ptr) && !is_unreserved(*ptr) && !is_reserved(*ptr) &&
                  !(flags & Uri_CREATE_NO_ENCODE_FORBIDDEN_CHARACTERS)) {
            if(!(is_file && (flags & Uri_CREATE_FILE_USE_DOS_PATH))) {
                if(!computeOnly)
                    pct_encode_val(*ptr, uri->canon_uri+uri->canon_len);
                uri->canon_len += 3;
                do_default_action = FALSE;
            }
        }

        if(do_default_action) {
            if(!computeOnly)
                uri->canon_uri[uri->canon_len] = *ptr;
            ++uri->canon_len;
        }
    }

    if(is_mk && !computeOnly && !(flags & Uri_CREATE_NO_CANONICALIZE)) {
        DWORD new_len = remove_dot_segments(uri->canon_uri + uri->path_start,
                                            uri->canon_len - uri->path_start);
        uri->canon_len = uri->path_start + new_len;
    }

    uri->path_len = uri->canon_len - uri->path_start;

    if(!computeOnly)
        TRACE("(%p %p %x %d): Canonicalized opaque URI path %s len=%d\n", data, uri, flags, computeOnly,
            debugstr_wn(uri->canon_uri+uri->path_start, uri->path_len), uri->path_len);
    return TRUE;
}