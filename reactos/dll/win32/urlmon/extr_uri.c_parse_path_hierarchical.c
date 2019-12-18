#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ scheme_type; char const* path; int path_len; int /*<<< orphan*/  must_have_path; } ;
typedef  TYPE_1__ parse_data ;
typedef  char WCHAR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  TRACE (char*,char const**,TYPE_1__*,int,...) ; 
 int TRUE ; 
 scalar_t__ URL_SCHEME_FILE ; 
 scalar_t__ URL_SCHEME_UNKNOWN ; 
 scalar_t__ URL_SCHEME_WILDCARD ; 
 int Uri_CREATE_FILE_USE_DOS_PATH ; 
 int Uri_CREATE_NO_CANONICALIZE ; 
 int /*<<< orphan*/  check_pct_encoded (char const**) ; 
 int /*<<< orphan*/  debugstr_wn (char const*,int) ; 
 scalar_t__ is_forbidden_dos_path_char (char const) ; 
 scalar_t__ is_path_delim (scalar_t__,char const) ; 

__attribute__((used)) static BOOL parse_path_hierarchical(const WCHAR **ptr, parse_data *data, DWORD flags) {
    const WCHAR *start = *ptr;
    static const WCHAR slash[] = {'/',0};
    const BOOL is_file = data->scheme_type == URL_SCHEME_FILE;

    if(is_path_delim(data->scheme_type, **ptr)) {
        if(data->scheme_type == URL_SCHEME_WILDCARD && !data->must_have_path) {
            data->path = NULL;
            data->path_len = 0;
        } else if(!(flags & Uri_CREATE_NO_CANONICALIZE)) {
            /* If the path component is empty, then a '/' is added. */
            data->path = slash;
            data->path_len = 1;
        }
    } else {
        while(!is_path_delim(data->scheme_type, **ptr)) {
            if(**ptr == '%' && data->scheme_type != URL_SCHEME_UNKNOWN && !is_file) {
                if(!check_pct_encoded(ptr)) {
                    *ptr = start;
                    return FALSE;
                } else
                    continue;
            } else if(is_forbidden_dos_path_char(**ptr) && is_file &&
                      (flags & Uri_CREATE_FILE_USE_DOS_PATH)) {
                /* File schemes with USE_DOS_PATH set aren't allowed to have
                 * a '<' or '>' or '\"' appear in them.
                 */
                *ptr = start;
                return FALSE;
            } else if(**ptr == '\\') {
                /* Not allowed to have a backslash if NO_CANONICALIZE is set
                 * and the scheme is known type (but not a file scheme).
                 */
                if(flags & Uri_CREATE_NO_CANONICALIZE) {
                    if(data->scheme_type != URL_SCHEME_FILE &&
                       data->scheme_type != URL_SCHEME_UNKNOWN) {
                        *ptr = start;
                        return FALSE;
                    }
                }
            }

            ++(*ptr);
        }

        /* The only time a URI doesn't have a path is when
         * the NO_CANONICALIZE flag is set and the raw URI
         * didn't contain one.
         */
        if(*ptr == start) {
            data->path = NULL;
            data->path_len = 0;
        } else {
            data->path = start;
            data->path_len = *ptr - start;
        }
    }

    if(data->path)
        TRACE("(%p %p %x): Parsed path %s len=%d\n", ptr, data, flags,
            debugstr_wn(data->path, data->path_len), data->path_len);
    else
        TRACE("(%p %p %x): The URI contained no path\n", ptr, data, flags);

    return TRUE;
}