#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mpu_status_port; } ;
typedef  TYPE_1__ snd_wavefront_midi_t ;

/* Variables and functions */
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int 
wf_mpu_status (snd_wavefront_midi_t *midi)

{
	return inb (midi->mpu_status_port);
}