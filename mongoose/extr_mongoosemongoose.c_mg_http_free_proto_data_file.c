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
struct mg_http_proto_data_file {int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct mg_http_proto_data_file*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mg_http_free_proto_data_file(struct mg_http_proto_data_file *d) {
  if (d != NULL) {
    if (d->fp != NULL) {
      fclose(d->fp);
    }
    memset(d, 0, sizeof(struct mg_http_proto_data_file));
  }
}