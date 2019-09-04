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
struct isight {scalar_t__ audio_base; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_READ_QUADLET_REQUEST ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reg_read(struct isight *isight, int offset, __be32 *value)
{
	return snd_fw_transaction(isight->unit, TCODE_READ_QUADLET_REQUEST,
				  isight->audio_base + offset, value, 4, 0);
}