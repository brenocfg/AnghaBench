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
struct orangefs_khandle {int /*<<< orphan*/  u; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (struct orangefs_khandle*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ORANGEFS_khandle_from(struct orangefs_khandle *kh,
				     void *p, int size)
{
	memset(kh, 0, 16);
	memcpy(kh->u, p, 16);

}