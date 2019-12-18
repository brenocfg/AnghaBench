#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct backtrace_location {char* filename; int lineno; scalar_t__ method_id; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
struct TYPE_2__ {scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* RDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_type ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ mrb_data_check_get_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 char* mrb_sym_name (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ packed_bt_len (struct backtrace_location const*,int) ; 
 int /*<<< orphan*/ * stderr ; 

__attribute__((used)) static void
print_packed_backtrace(mrb_state *mrb, mrb_value packed)
{
  FILE *stream = stderr;
  const struct backtrace_location *bt;
  int n, i;
  int ai = mrb_gc_arena_save(mrb);

  bt = (struct backtrace_location*)mrb_data_check_get_ptr(mrb, packed, &bt_type);
  if (bt == NULL) return;
  n = (mrb_int)RDATA(packed)->flags;

  if (packed_bt_len(bt, n) == 0) return;
  fprintf(stream, "trace (most recent call last):\n");
  for (i = 0; i<n; i++) {
    const struct backtrace_location *entry = &bt[n-i-1];
    if (entry->filename == NULL) continue;
    fprintf(stream, "\t[%d] %s:%d", i, entry->filename, entry->lineno);
    if (entry->method_id != 0) {
      const char *method_name;

      method_name = mrb_sym_name(mrb, entry->method_id);
      fprintf(stream, ":in %s", method_name);
      mrb_gc_arena_restore(mrb, ai);
    }
    fprintf(stream, "\n");
  }
}