#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ scheme_type; scalar_t__ host_len; int /*<<< orphan*/  has_implicit_scheme; int /*<<< orphan*/  path_len; int /*<<< orphan*/  path; scalar_t__ username; scalar_t__ password; scalar_t__ is_relative; scalar_t__ has_port; scalar_t__ host; int /*<<< orphan*/  is_opaque; } ;
typedef  TYPE_1__ parse_data ;
struct TYPE_12__ {size_t canon_len; char* canon_uri; size_t path_start; int path_len; int userinfo_start; int userinfo_split; int host_start; int authority_start; int domain_offset; int port_offset; int extension_offset; int /*<<< orphan*/  port; void* has_port; int /*<<< orphan*/  display_modifiers; scalar_t__ authority_len; int /*<<< orphan*/  host_type; scalar_t__ host_len; scalar_t__ userinfo_len; } ;
typedef  TYPE_2__ Uri ;
struct TYPE_13__ {scalar_t__ scheme; int /*<<< orphan*/  port; } ;
typedef  size_t INT ;
typedef  size_t DWORD ;
typedef  void* BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_3__*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  URI_DISPLAY_NO_ABSOLUTE_URI ; 
 scalar_t__ URL_SCHEME_WILDCARD ; 
 int /*<<< orphan*/  Uri_HOST_UNKNOWN ; 
 int /*<<< orphan*/  canonicalize_authority (TYPE_1__ const*,TYPE_2__*,size_t,void*) ; 
 int canonicalize_path_hierarchical (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,size_t,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  canonicalize_path_opaque (TYPE_1__ const*,TYPE_2__*,size_t,void*) ; 
 TYPE_3__* default_ports ; 
 int find_file_extension (char*,int) ; 
 scalar_t__ is_hierarchical_scheme (scalar_t__) ; 

__attribute__((used)) static BOOL canonicalize_hierpart(const parse_data *data, Uri *uri, DWORD flags, BOOL computeOnly) {
    if(!data->is_opaque || (data->is_relative && (data->password || data->username))) {
        /* "//" is only added for non-wildcard scheme types.
         *
         * A "//" is only added to a relative URI if it has a
         * host or port component (this only happens if a IUriBuilder
         * is generating an IUri).
         */
        if((data->is_relative && (data->host || data->has_port)) ||
           (!data->is_relative && data->scheme_type != URL_SCHEME_WILDCARD)) {
            if(data->scheme_type == URL_SCHEME_WILDCARD)
                FIXME("Here\n");

            if(!computeOnly) {
                INT pos = uri->canon_len;

                uri->canon_uri[pos] = '/';
                uri->canon_uri[pos+1] = '/';
           }
           uri->canon_len += 2;
        }

        if(!canonicalize_authority(data, uri, flags, computeOnly))
            return FALSE;

        if(data->is_relative && (data->password || data->username)) {
            if(!canonicalize_path_opaque(data, uri, flags, computeOnly))
                return FALSE;
        } else {
            if(!computeOnly)
                uri->path_start = uri->canon_len;
            uri->path_len = canonicalize_path_hierarchical(data->path, data->path_len, data->scheme_type, data->host_len != 0,
                    flags, data->has_implicit_scheme, computeOnly ? NULL : uri->canon_uri+uri->canon_len);
            uri->canon_len += uri->path_len;
            if(!computeOnly && !uri->path_len)
                uri->path_start = -1;
        }
    } else {
        /* Opaque URI's don't have an authority. */
        uri->userinfo_start = uri->userinfo_split = -1;
        uri->userinfo_len = 0;
        uri->host_start = -1;
        uri->host_len = 0;
        uri->host_type = Uri_HOST_UNKNOWN;
        uri->has_port = FALSE;
        uri->authority_start = -1;
        uri->authority_len = 0;
        uri->domain_offset = -1;
        uri->port_offset = -1;

        if(is_hierarchical_scheme(data->scheme_type)) {
            DWORD i;

            /* Absolute URIs aren't displayed for known scheme types
             * which should be hierarchical URIs.
             */
            uri->display_modifiers |= URI_DISPLAY_NO_ABSOLUTE_URI;

            /* Windows also sets the port for these (if they have one). */
            for(i = 0; i < ARRAY_SIZE(default_ports); ++i) {
                if(data->scheme_type == default_ports[i].scheme) {
                    uri->has_port = TRUE;
                    uri->port = default_ports[i].port;
                    break;
                }
            }
        }

        if(!canonicalize_path_opaque(data, uri, flags, computeOnly))
            return FALSE;
    }

    if(uri->path_start > -1 && !computeOnly)
        /* Finding file extensions happens for both types of URIs. */
        uri->extension_offset = find_file_extension(uri->canon_uri+uri->path_start, uri->path_len);
    else
        uri->extension_offset = -1;

    return TRUE;
}