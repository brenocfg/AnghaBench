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
struct nau8824 {int /*<<< orphan*/  jd_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void nau8824_sema_release(struct nau8824 *nau8824)
{
	up(&nau8824->jd_sem);
}