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
struct dso {scalar_t__ binary_type; } ;

/* Variables and functions */
 scalar_t__ DSO_BINARY_TYPE__GUEST_KCORE ; 
 scalar_t__ DSO_BINARY_TYPE__KCORE ; 

__attribute__((used)) static inline bool dso__is_kcore(struct dso *dso)
{
	return dso->binary_type == DSO_BINARY_TYPE__KCORE ||
	       dso->binary_type == DSO_BINARY_TYPE__GUEST_KCORE;
}