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
struct mg_connection {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 size_t mg_fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,char*,size_t) ; 

__attribute__((used)) static void mg_send_file_data(struct mg_connection *nc, FILE *fp) {
  char buf[BUFSIZ];
  size_t n;
  while ((n = mg_fread(buf, 1, sizeof(buf), fp)) > 0) {
    mg_send(nc, buf, n);
  }
}