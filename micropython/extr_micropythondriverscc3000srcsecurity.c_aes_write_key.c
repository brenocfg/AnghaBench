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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  AES128_KEY_SIZE ; 
 int /*<<< orphan*/  NVMEM_AES128_KEY_FILEID ; 
 int /*<<< orphan*/  nvmem_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

INT32 aes_write_key(UINT8 *key)
{
	INT32	returnValue;

	returnValue = nvmem_write(NVMEM_AES128_KEY_FILEID, AES128_KEY_SIZE, 0, key);

	return returnValue;
}