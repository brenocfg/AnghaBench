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
struct TYPE_10__ {scalar_t__ host_len; int /*<<< orphan*/  host_type; int /*<<< orphan*/  const* host; } ;
typedef  TYPE_2__ parse_data ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {scalar_t__ host_len; int modified_props; TYPE_1__* uri; int /*<<< orphan*/ * host; } ;
typedef  TYPE_3__ UriBuilder ;
struct TYPE_9__ {int host_start; scalar_t__ host_len; int /*<<< orphan*/ * canon_uri; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ALLOW_BRACKETLESS_IP_LITERAL ; 
 scalar_t__ IGNORE_PORT_DELIMITER ; 
 int /*<<< orphan*/  INET_E_INVALID_URL ; 
 scalar_t__ SKIP_IP_FUTURE_CHECK ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__ const*,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int Uri_HAS_HOST ; 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ parse_host (int /*<<< orphan*/  const**,TYPE_2__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static HRESULT validate_host(const UriBuilder *builder, parse_data *data, DWORD flags) {
    const WCHAR *ptr;
    const WCHAR **pptr;
    DWORD expected_len;

    if(builder->host) {
        ptr = builder->host;
        expected_len = builder->host_len;
    } else if(!(builder->modified_props & Uri_HAS_HOST) && builder->uri && builder->uri->host_start > -1) {
        ptr = builder->uri->canon_uri + builder->uri->host_start;
        expected_len = builder->uri->host_len;
    } else
        ptr = NULL;

    if(ptr) {
        const WCHAR *component = ptr;
        DWORD extras = ALLOW_BRACKETLESS_IP_LITERAL|IGNORE_PORT_DELIMITER|SKIP_IP_FUTURE_CHECK;
        pptr = &ptr;

        if(parse_host(pptr, data, flags, extras) && data->host_len == expected_len)
            TRACE("(%p %p %x): Found valid host name %s len=%d type=%d.\n", builder, data, flags,
                debugstr_wn(data->host, data->host_len), data->host_len, data->host_type);
        else {
            TRACE("(%p %p %x): Invalid host name found %s.\n", builder, data, flags,
                debugstr_wn(component, expected_len));
            return INET_E_INVALID_URL;
        }
    }

    return S_OK;
}