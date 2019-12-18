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
struct TYPE_2__ {char const* errstr; int errno; } ;

/* Variables and functions */
 TYPE_1__* wavefront_errors ; 

__attribute__((used)) static const char *
wavefront_errorstr (int errnum)

{
	int i;

	for (i = 0; wavefront_errors[i].errstr; i++) {
		if (wavefront_errors[i].errno == errnum) {
			return wavefront_errors[i].errstr;
		}
	}

	return "Unknown WaveFront error";
}