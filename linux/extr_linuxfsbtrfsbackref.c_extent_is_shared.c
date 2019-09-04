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
struct share_check {int share_count; } ;

/* Variables and functions */
 int BACKREF_FOUND_SHARED ; 

__attribute__((used)) static inline int extent_is_shared(struct share_check *sc)
{
	return (sc && sc->share_count > 1) ? BACKREF_FOUND_SHARED : 0;
}