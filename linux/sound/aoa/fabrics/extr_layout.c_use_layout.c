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
struct layout {TYPE_1__* codecs; } ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 int MAX_CODECS_PER_BUS ; 
 int /*<<< orphan*/  request_module (char*,scalar_t__) ; 

__attribute__((used)) static void use_layout(struct layout *l)
{
	int i;

	for (i=0; i<MAX_CODECS_PER_BUS; i++) {
		if (l->codecs[i].name) {
			request_module("snd-aoa-codec-%s", l->codecs[i].name);
		}
	}
	/* now we wait for the codecs to call us back */
}