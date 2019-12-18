#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  protocol; } ;
typedef  TYPE_1__ stgmed_buf_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ IInternetProtocolEx_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 

__attribute__((used)) static void read_protocol_data(stgmed_buf_t *stgmed_buf)
{
    BYTE buf[8192];
    DWORD read;
    HRESULT hres;

    do hres = IInternetProtocolEx_Read(stgmed_buf->protocol, buf, sizeof(buf), &read);
    while(hres == S_OK);
}