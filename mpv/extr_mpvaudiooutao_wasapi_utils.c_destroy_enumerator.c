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
struct enumerator {int /*<<< orphan*/  pEnumerator; int /*<<< orphan*/  pDevices; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAFE_RELEASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct enumerator*) ; 

__attribute__((used)) static void destroy_enumerator(struct enumerator *e)
{
    if (!e)
        return;
    SAFE_RELEASE(e->pDevices);
    SAFE_RELEASE(e->pEnumerator);
    talloc_free(e);
}