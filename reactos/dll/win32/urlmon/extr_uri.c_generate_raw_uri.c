#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* scheme; int scheme_len; scalar_t__ scheme_type; char* host; char* username; int username_len; char* password; int password_len; scalar_t__ host_type; int host_len; scalar_t__ port_value; char* path; int path_len; char* query; int query_len; char* fragment; int fragment_len; int /*<<< orphan*/  is_opaque; scalar_t__ has_port; } ;
typedef  TYPE_1__ parse_data ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {scalar_t__ scheme; scalar_t__ port; } ;
typedef  int DWORD ;
typedef  char* BSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int FALSE ; 
 int RAW_URI_CONVERT_TO_DOS_PATH ; 
 int RAW_URI_FORCE_PORT_DISP ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__ const*,char*,int,...) ; 
 int TRUE ; 
 scalar_t__ URL_SCHEME_FILE ; 
 scalar_t__ Uri_HOST_IPV6 ; 
 int /*<<< orphan*/  convert_to_dos_path (char*,int,char*,int*) ; 
 int /*<<< orphan*/  debugstr_wn (char*,int) ; 
 TYPE_3__* default_ports ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ ui2str (char*,scalar_t__) ; 

__attribute__((used)) static DWORD generate_raw_uri(const parse_data *data, BSTR uri, DWORD flags) {
    DWORD length = 0;

    if(data->scheme) {
        if(uri) {
            memcpy(uri, data->scheme, data->scheme_len*sizeof(WCHAR));
            uri[data->scheme_len] = ':';
        }
        length += data->scheme_len+1;
    }

    if(!data->is_opaque) {
        /* For the "//" which appears before the authority component. */
        if(uri) {
            uri[length] = '/';
            uri[length+1] = '/';
        }
        length += 2;

        /* Check if we need to add the "\\" before the host name
         * of a UNC server name in a DOS path.
         */
        if(flags & RAW_URI_CONVERT_TO_DOS_PATH &&
           data->scheme_type == URL_SCHEME_FILE && data->host) {
            if(uri) {
                uri[length] = '\\';
                uri[length+1] = '\\';
            }
            length += 2;
        }
    }

    if(data->username) {
        if(uri)
            memcpy(uri+length, data->username, data->username_len*sizeof(WCHAR));
        length += data->username_len;
    }

    if(data->password) {
        if(uri) {
            uri[length] = ':';
            memcpy(uri+length+1, data->password, data->password_len*sizeof(WCHAR));
        }
        length += data->password_len+1;
    }

    if(data->password || data->username) {
        if(uri)
            uri[length] = '@';
        ++length;
    }

    if(data->host) {
        /* IPv6 addresses get the brackets added around them if they don't already
         * have them.
         */
        const BOOL add_brackets = data->host_type == Uri_HOST_IPV6 && *(data->host) != '[';
        if(add_brackets) {
            if(uri)
                uri[length] = '[';
            ++length;
        }

        if(uri)
            memcpy(uri+length, data->host, data->host_len*sizeof(WCHAR));
        length += data->host_len;

        if(add_brackets) {
            if(uri)
                uri[length] = ']';
            length++;
        }
    }

    if(data->has_port) {
        /* The port isn't included in the raw uri if it's the default
         * port for the scheme type.
         */
        DWORD i;
        BOOL is_default = FALSE;

        for(i = 0; i < ARRAY_SIZE(default_ports); ++i) {
            if(data->scheme_type == default_ports[i].scheme &&
               data->port_value == default_ports[i].port)
                is_default = TRUE;
        }

        if(!is_default || flags & RAW_URI_FORCE_PORT_DISP) {
            if(uri)
                uri[length] = ':';
            ++length;

            if(uri)
                length += ui2str(uri+length, data->port_value);
            else
                length += ui2str(NULL, data->port_value);
        }
    }

    /* Check if a '/' should be added before the path for hierarchical URIs. */
    if(!data->is_opaque && data->path && *(data->path) != '/') {
        if(uri)
            uri[length] = '/';
        ++length;
    }

    if(data->path) {
        if(!data->is_opaque && data->scheme_type == URL_SCHEME_FILE &&
           flags & RAW_URI_CONVERT_TO_DOS_PATH) {
            DWORD len = 0;

            if(uri)
                convert_to_dos_path(data->path, data->path_len, uri+length, &len);
            else
                convert_to_dos_path(data->path, data->path_len, NULL, &len);

            length += len;
        } else {
            if(uri)
                memcpy(uri+length, data->path, data->path_len*sizeof(WCHAR));
            length += data->path_len;
        }
    }

    if(data->query) {
        if(uri)
            memcpy(uri+length, data->query, data->query_len*sizeof(WCHAR));
        length += data->query_len;
    }

    if(data->fragment) {
        if(uri)
            memcpy(uri+length, data->fragment, data->fragment_len*sizeof(WCHAR));
        length += data->fragment_len;
    }

    if(uri)
        TRACE("(%p %p): Generated raw uri=%s len=%d\n", data, uri, debugstr_wn(uri, length), length);
    else
        TRACE("(%p %p): Computed raw uri len=%d\n", data, uri, length);

    return length;
}