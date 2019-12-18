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
struct echoaudio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct audiopipe {TYPE_1__ sgpage; } ;

/* Variables and functions */
 int sglist_add_mapping (struct echoaudio*,struct audiopipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sglist_wrap(struct echoaudio *chip, struct audiopipe *pipe)
{
	return sglist_add_mapping(chip, pipe, pipe->sgpage.addr, 0);
}