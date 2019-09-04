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
struct u132_endp {int /*<<< orphan*/  kref; } ;
struct u132 {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void u132_endp_init_kref(struct u132 *u132,
	struct u132_endp *endp)
{
	kref_init(&endp->kref);
	kref_get(&u132->kref);
}