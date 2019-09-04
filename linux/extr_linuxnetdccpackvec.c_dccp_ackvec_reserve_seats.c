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
typedef  scalar_t__ u16 ;
struct dccp_ackvec {scalar_t__ av_buf; int /*<<< orphan*/  av_buf_head; } ;

/* Variables and functions */
 scalar_t__ DCCPAV_MAX_ACKVEC_LEN ; 
 int /*<<< orphan*/  DCCPAV_NOT_RECEIVED ; 
 scalar_t__ __ackvec_idx_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dccp_ackvec_reserve_seats(struct dccp_ackvec *av, u16 num)
{
	u16 start = __ackvec_idx_add(av->av_buf_head, 1),
	    len	  = DCCPAV_MAX_ACKVEC_LEN - start;

	/* check for buffer wrap-around */
	if (num > len) {
		memset(av->av_buf + start, DCCPAV_NOT_RECEIVED, len);
		start = 0;
		num  -= len;
	}
	if (num)
		memset(av->av_buf + start, DCCPAV_NOT_RECEIVED, num);
}