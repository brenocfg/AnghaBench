#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  uri; void* scheme_type; scalar_t__ is_relative; scalar_t__ scheme_len; scalar_t__ scheme; } ;
typedef  TYPE_1__ parse_data ;
struct TYPE_7__ {void* scheme; int /*<<< orphan*/  scheme_name; } ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCmpNIW (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 void* URL_SCHEME_UNKNOWN ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ lstrlenW (int /*<<< orphan*/ ) ; 
 TYPE_2__* recognized_schemes ; 

__attribute__((used)) static BOOL parse_scheme_type(parse_data *data) {
    /* If there's scheme data then see if it's a recognized scheme. */
    if(data->scheme && data->scheme_len) {
        DWORD i;

        for(i = 0; i < ARRAY_SIZE(recognized_schemes); ++i) {
            if(lstrlenW(recognized_schemes[i].scheme_name) == data->scheme_len) {
                /* Has to be a case insensitive compare. */
                if(!StrCmpNIW(recognized_schemes[i].scheme_name, data->scheme, data->scheme_len)) {
                    data->scheme_type = recognized_schemes[i].scheme;
                    return TRUE;
                }
            }
        }

        /* If we get here it means it's not a recognized scheme. */
        data->scheme_type = URL_SCHEME_UNKNOWN;
        return TRUE;
    } else if(data->is_relative) {
        /* Relative URI's have no scheme. */
        data->scheme_type = URL_SCHEME_UNKNOWN;
        return TRUE;
    } else {
        /* Should never reach here! what happened... */
        FIXME("(%p): Unable to determine scheme type for URI %s\n", data, debugstr_w(data->uri));
        return FALSE;
    }
}