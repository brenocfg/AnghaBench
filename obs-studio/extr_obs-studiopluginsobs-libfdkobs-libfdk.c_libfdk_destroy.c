#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* packet_buffer; int /*<<< orphan*/  fdkhandle; } ;
typedef  TYPE_1__ libfdk_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  aacEncClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void libfdk_destroy(void *data)
{
	libfdk_encoder_t *enc = data;

	aacEncClose(&enc->fdkhandle);

	bfree(enc->packet_buffer);
	bfree(enc);

	blog(LOG_INFO, "libfdk_aac encoder destroyed");
}