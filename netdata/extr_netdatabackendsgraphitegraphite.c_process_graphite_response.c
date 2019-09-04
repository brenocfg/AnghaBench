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
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int discard_response (int /*<<< orphan*/ *,char*) ; 

int process_graphite_response(BUFFER *b) {
    return discard_response(b, "graphite");
}