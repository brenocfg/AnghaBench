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
struct l2tp_session {int l2specific_type; } ;

/* Variables and functions */
#define  L2TP_L2SPECTYPE_DEFAULT 129 
#define  L2TP_L2SPECTYPE_NONE 128 

__attribute__((used)) static inline int l2tp_get_l2specific_len(struct l2tp_session *session)
{
	switch (session->l2specific_type) {
	case L2TP_L2SPECTYPE_DEFAULT:
		return 4;
	case L2TP_L2SPECTYPE_NONE:
	default:
		return 0;
	}
}