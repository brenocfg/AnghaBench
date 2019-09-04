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
struct extent_status {unsigned int es_pblk; } ;

/* Variables and functions */
 unsigned int ES_SHIFT ; 

__attribute__((used)) static inline unsigned int ext4_es_status(struct extent_status *es)
{
	return es->es_pblk >> ES_SHIFT;
}