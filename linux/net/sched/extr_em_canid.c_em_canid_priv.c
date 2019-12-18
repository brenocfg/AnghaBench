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
struct tcf_ematch {scalar_t__ data; } ;
struct canid_match {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct canid_match *em_canid_priv(struct tcf_ematch *m)
{
	return (struct canid_match *)m->data;
}