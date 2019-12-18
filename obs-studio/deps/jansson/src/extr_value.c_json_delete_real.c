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
typedef  int /*<<< orphan*/  json_real_t ;

/* Variables and functions */
 int /*<<< orphan*/  jsonp_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void json_delete_real(json_real_t *real)
{
    jsonp_free(real);
}