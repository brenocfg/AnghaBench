#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  checksum; } ;
struct rxkad_response {TYPE_1__ encrypted; } ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (int) ; 

__attribute__((used)) static void rxkad_calc_response_checksum(struct rxkad_response *response)
{
	u32 csum = 1000003;
	int loop;
	u8 *p = (u8 *) response;

	for (loop = sizeof(*response); loop > 0; loop--)
		csum = csum * 0x10204081 + *p++;

	response->encrypted.checksum = htonl(csum);
}