#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int username_len; int /*<<< orphan*/  const* username; } ;
typedef  TYPE_2__ parse_data ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {int username_len; int modified_props; TYPE_1__* uri; int /*<<< orphan*/ * username; } ;
typedef  TYPE_3__ UriBuilder ;
struct TYPE_9__ {int userinfo_start; int userinfo_split; int userinfo_len; int /*<<< orphan*/  const* canon_uri; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOW_NULL_TERM_USER_NAME ; 
 int /*<<< orphan*/  INET_E_INVALID_URL ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__ const*,TYPE_2__*,int,int /*<<< orphan*/ ,...) ; 
 int Uri_HAS_USER_NAME ; 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ parse_username (int /*<<< orphan*/  const**,TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT validate_username(const UriBuilder *builder, parse_data *data, DWORD flags) {
    const WCHAR *ptr;
    const WCHAR **pptr;
    DWORD expected_len;

    if(builder->username) {
        ptr = builder->username;
        expected_len = builder->username_len;
    } else if(!(builder->modified_props & Uri_HAS_USER_NAME) && builder->uri &&
              builder->uri->userinfo_start > -1 && builder->uri->userinfo_split != 0) {
        /* Just use the username from the base Uri. */
        data->username = builder->uri->canon_uri+builder->uri->userinfo_start;
        data->username_len = (builder->uri->userinfo_split > -1) ?
                                        builder->uri->userinfo_split : builder->uri->userinfo_len;
        ptr = NULL;
    } else {
        ptr = NULL;
        expected_len = 0;
    }

    if(ptr) {
        const WCHAR *component = ptr;
        pptr = &ptr;
        if(parse_username(pptr, data, flags, ALLOW_NULL_TERM_USER_NAME) &&
           data->username_len == expected_len)
            TRACE("(%p %p %x): Found valid username component %s len=%d.\n", builder, data, flags,
                debugstr_wn(data->username, data->username_len), data->username_len);
        else {
            TRACE("(%p %p %x): Invalid username component found %s.\n", builder, data, flags,
                debugstr_wn(component, expected_len));
            return INET_E_INVALID_URL;
        }
    }

    return S_OK;
}