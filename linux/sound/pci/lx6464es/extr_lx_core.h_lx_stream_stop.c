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
typedef  int /*<<< orphan*/  u32 ;
struct lx6464es {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSTATE_STOP ; 
 int lx_stream_set_state (struct lx6464es*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 

__attribute__((used)) static inline int lx_stream_stop(struct lx6464es *chip, u32 pipe,
				 int is_capture)
{
	snd_printdd("->lx_stream_stop\n");
	return lx_stream_set_state(chip, pipe, is_capture, SSTATE_STOP);
}