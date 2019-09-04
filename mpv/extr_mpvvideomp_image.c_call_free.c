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
typedef  int /*<<< orphan*/  uint8_t ;
struct free_args {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct free_args*) ; 

__attribute__((used)) static void call_free(void *opaque, uint8_t *data)
{
    struct free_args *args = opaque;
    args->free(args->arg);
    talloc_free(args);
}