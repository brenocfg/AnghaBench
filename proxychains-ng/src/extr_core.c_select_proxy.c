#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int select_type ;
struct TYPE_4__ {scalar_t__ ps; } ;
typedef  TYPE_1__ proxy_data ;

/* Variables and functions */
#define  FIFOLY 129 
 scalar_t__ PLAY_STATE ; 
#define  RANDOMLY 128 
 unsigned int rand () ; 

__attribute__((used)) static proxy_data *select_proxy(select_type how, proxy_data * pd, unsigned int proxy_count, unsigned int *offset) {
	unsigned int i = 0, k = 0;
	if(*offset >= proxy_count)
		return NULL;
	switch (how) {
		case RANDOMLY:
			do {
				k++;
				i = rand() % proxy_count;
			} while(pd[i].ps != PLAY_STATE && k < proxy_count * 100);
			break;
		case FIFOLY:
			for(i = *offset; i < proxy_count; i++) {
				if(pd[i].ps == PLAY_STATE) {
					*offset = i;
					break;
				}
			}
		default:
			break;
	}
	if(i >= proxy_count)
		i = 0;
	return (pd[i].ps == PLAY_STATE) ? &pd[i] : NULL;
}