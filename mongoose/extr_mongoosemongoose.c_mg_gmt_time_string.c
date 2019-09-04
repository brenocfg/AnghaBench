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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  gmtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strftime (char*,size_t,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mg_gmt_time_string(char *buf, size_t buf_len, time_t *t) {
  strftime(buf, buf_len, "%a, %d %b %Y %H:%M:%S GMT", gmtime(t));
}