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
struct TYPE_10__ {scalar_t__ scheme_len; int /*<<< orphan*/  const* scheme; } ;
typedef  TYPE_2__ parse_data ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {scalar_t__ scheme_len; TYPE_1__* uri; int /*<<< orphan*/ * scheme; } ;
typedef  TYPE_3__ UriBuilder ;
struct TYPE_9__ {int scheme_start; scalar_t__ scheme_len; int /*<<< orphan*/ * canon_uri; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOW_NULL_TERM_SCHEME ; 
 int /*<<< orphan*/  INET_E_INVALID_URL ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__ const*,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ parse_scheme (int /*<<< orphan*/  const**,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT validate_scheme_name(const UriBuilder *builder, parse_data *data, DWORD flags) {
    const WCHAR *component;
    const WCHAR *ptr;
    const WCHAR **pptr;
    DWORD expected_len;

    if(builder->scheme) {
        ptr = builder->scheme;
        expected_len = builder->scheme_len;
    } else if(builder->uri && builder->uri->scheme_start > -1) {
        ptr = builder->uri->canon_uri+builder->uri->scheme_start;
        expected_len = builder->uri->scheme_len;
    } else {
        static const WCHAR nullW[] = {0};
        ptr = nullW;
        expected_len = 0;
    }

    component = ptr;
    pptr = &ptr;
    if(parse_scheme(pptr, data, flags, ALLOW_NULL_TERM_SCHEME) &&
       data->scheme_len == expected_len) {
        if(data->scheme)
            TRACE("(%p %p %x): Found valid scheme component %s len=%d.\n", builder, data, flags,
               debugstr_wn(data->scheme, data->scheme_len), data->scheme_len);
    } else {
        TRACE("(%p %p %x): Invalid scheme component found %s.\n", builder, data, flags,
            debugstr_wn(component, expected_len));
        return INET_E_INVALID_URL;
   }

    return S_OK;
}