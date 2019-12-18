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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct csum_state {int size; } ;

/* Variables and functions */
#define  CSUM_TYPE_16 130 
#define  CSUM_TYPE_32 129 
#define  CSUM_TYPE_8 128 
 int /*<<< orphan*/  csum16_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct csum_state*) ; 
 int /*<<< orphan*/  csum32_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct csum_state*) ; 
 int /*<<< orphan*/  csum8_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct csum_state*) ; 

void
csum_update(uint8_t *p, uint32_t len, struct csum_state *css)
{
	switch (css->size) {
	case CSUM_TYPE_8:
		csum8_update(p,len,css);
		break;
	case CSUM_TYPE_16:
		csum16_update(p,len,css);
		break;
	case CSUM_TYPE_32:
		csum32_update(p,len,css);
		break;
	}
}