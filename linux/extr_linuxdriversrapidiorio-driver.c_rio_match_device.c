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
struct rio_device_id {scalar_t__ vid; scalar_t__ asm_vid; scalar_t__ did; scalar_t__ asm_did; } ;
struct rio_dev {scalar_t__ vid; scalar_t__ did; scalar_t__ asm_vid; scalar_t__ asm_did; } ;

/* Variables and functions */
 scalar_t__ RIO_ANY_ID ; 

__attribute__((used)) static const struct rio_device_id *rio_match_device(const struct rio_device_id
						    *id,
						    const struct rio_dev *rdev)
{
	while (id->vid || id->asm_vid) {
		if (((id->vid == RIO_ANY_ID) || (id->vid == rdev->vid)) &&
		    ((id->did == RIO_ANY_ID) || (id->did == rdev->did)) &&
		    ((id->asm_vid == RIO_ANY_ID)
		     || (id->asm_vid == rdev->asm_vid))
		    && ((id->asm_did == RIO_ANY_ID)
			|| (id->asm_did == rdev->asm_did)))
			return id;
		id++;
	}
	return NULL;
}