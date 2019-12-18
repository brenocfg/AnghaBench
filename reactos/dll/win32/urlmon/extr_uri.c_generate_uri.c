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
typedef  int /*<<< orphan*/  parse_data ;
typedef  int /*<<< orphan*/  UriBuilder ;
struct TYPE_4__ {int /*<<< orphan*/  create_flags; int /*<<< orphan*/ * raw_uri; } ;
typedef  TYPE_1__ Uri ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ INET_E_INVALID_URL ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * SysAllocStringLen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ canonicalize_uri (int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_raw_uri (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT generate_uri(const UriBuilder *builder, const parse_data *data, Uri *uri, DWORD flags) {
    HRESULT hr;
    DWORD length = generate_raw_uri(data, NULL, 0);
    uri->raw_uri = SysAllocStringLen(NULL, length);
    if(!uri->raw_uri)
        return E_OUTOFMEMORY;

    generate_raw_uri(data, uri->raw_uri, 0);

    hr = canonicalize_uri(data, uri, flags);
    if(FAILED(hr)) {
        if(hr == E_INVALIDARG)
            return INET_E_INVALID_URL;
        return hr;
    }

    uri->create_flags = flags;
    return S_OK;
}