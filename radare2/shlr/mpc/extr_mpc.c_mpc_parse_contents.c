#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  error; int /*<<< orphan*/ * output; } ;
typedef  TYPE_1__ mpc_result_t ;
typedef  int /*<<< orphan*/  mpc_parser_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  mpc_err_file (char const*,char*) ; 
 int mpc_parse_file (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

int mpc_parse_contents(const char *filename, mpc_parser_t *p, mpc_result_t *r) {
  
  FILE *f = fopen(filename, "rb");
  int res;
  
  if (!f) {
    r->output = NULL;
    r->error = mpc_err_file(filename, "Unable to open file!");
    return 0;
  }
  
  res = mpc_parse_file(filename, f, p, r);
  fclose(f);
  return res;
}