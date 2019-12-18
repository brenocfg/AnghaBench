#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  szStringData ; 
 int /*<<< orphan*/  szStringPool ; 
 scalar_t__ write_stream_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

HRESULT msi_init_string_table( IStorage *stg )
{
    USHORT zero[2] = { 0, 0 };
    UINT ret;

    /* create the StringPool stream... add the zero string to it*/
    ret = write_stream_data(stg, szStringPool, zero, sizeof zero, TRUE);
    if (ret != ERROR_SUCCESS)
        return E_FAIL;

    /* create the StringData stream... make it zero length */
    ret = write_stream_data(stg, szStringData, NULL, 0, TRUE);
    if (ret != ERROR_SUCCESS)
        return E_FAIL;

    return S_OK;
}