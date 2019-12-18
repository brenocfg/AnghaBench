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

/* Variables and functions */
 int /*<<< orphan*/  MUX_FOOTER (int) ; 
 int /*<<< orphan*/  MUX_HEADER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwrap_send (char const*) ; 
 int /*<<< orphan*/  rcv_clear () ; 
 int /*<<< orphan*/  strlen (char*) ; 

void iwrap_mux_send(const char *s) {
    rcv_clear();
    MUX_HEADER(0xff, strlen((char *)s));
    iwrap_send(s);
    MUX_FOOTER(0xff);
}