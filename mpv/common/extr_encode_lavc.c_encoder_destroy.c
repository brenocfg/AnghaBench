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
struct encoder_context {int /*<<< orphan*/  twopass_bytebuffer; int /*<<< orphan*/  encoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_stream (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encoder_destroy(void *ptr)
{
    struct encoder_context *p = ptr;

    avcodec_free_context(&p->encoder);
    free_stream(p->twopass_bytebuffer);
}