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
struct evlist {int dummy; } ;

/* Variables and functions */
 int bpf__strerror_setup_output_event (struct evlist*,int,char*,size_t) ; 

__attribute__((used)) static inline int bpf__strerror_setup_stdout(struct evlist *evlist, int err, char *buf, size_t size)
{
	return bpf__strerror_setup_output_event(evlist, err, buf, size);
}