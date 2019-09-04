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
struct pcmcia_loop_get {size_t len; unsigned char** buf; } ;
struct pcmcia_device {int dummy; } ;
typedef  int /*<<< orphan*/  cisdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  pcmcia_do_get_tuple ; 
 int /*<<< orphan*/  pcmcia_loop_tuple (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pcmcia_loop_get*) ; 

size_t pcmcia_get_tuple(struct pcmcia_device *p_dev, cisdata_t code,
			unsigned char **buf)
{
	struct pcmcia_loop_get get = {
		.len = 0,
		.buf = buf,
	};

	*get.buf = NULL;
	pcmcia_loop_tuple(p_dev, code, pcmcia_do_get_tuple, &get);

	return get.len;
}