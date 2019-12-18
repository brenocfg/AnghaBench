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
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 scalar_t__ SP_PORTION_SIZE ; 
 scalar_t__ nvmem_write (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 

UINT8 nvmem_write_patch(UINT32 ulFileId, UINT32 spLength, const UINT8 *spData)
{
	UINT8 	status = 0;
	UINT16	offset = 0;
	UINT8*      spDataPtr = (UINT8*)spData;

	while ((status == 0) && (spLength >= SP_PORTION_SIZE))
	{
		status = nvmem_write(ulFileId, SP_PORTION_SIZE, offset, spDataPtr);
		offset += SP_PORTION_SIZE;
		spLength -= SP_PORTION_SIZE;
		spDataPtr += SP_PORTION_SIZE;
	}

	if (status !=0)
	{
		// NVMEM error occurred
		return status;
	}

	if (spLength != 0)
	{
		// if reached here, a reminder is left
		status = nvmem_write(ulFileId, spLength, offset, spDataPtr);
	}

	return status;
}