#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int prev; int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ symbol_name ;
typedef  size_t mrb_sym ;
struct TYPE_5__ {size_t* symhash; TYPE_1__* symtbl; } ;
typedef  TYPE_2__ mrb_state ;

/* Variables and functions */
 size_t SYMBOL_NORMAL_SHIFT ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 size_t sym_inline_pack (char const*,int /*<<< orphan*/ ) ; 
 size_t symhash (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_sym
find_symbol(mrb_state *mrb, const char *name, uint16_t len, uint8_t *hashp)
{
  mrb_sym i;
  symbol_name *sname;
  uint8_t hash;

  /* inline symbol */
  i = sym_inline_pack(name, len);
  if (i > 0) return i;

  hash = symhash(name, len);
  if (hashp) *hashp = hash;

  i = mrb->symhash[hash];
  if (i == 0) return 0;
  do {
    sname = &mrb->symtbl[i];
    if (sname->len == len && memcmp(sname->name, name, len) == 0) {
      return i<<SYMBOL_NORMAL_SHIFT;
    }
    if (sname->prev == 0xff) {
      i -= 0xff;
      sname = &mrb->symtbl[i];
      while (mrb->symtbl < sname) {
        if (sname->len == len && memcmp(sname->name, name, len) == 0) {
          return (mrb_sym)(sname - mrb->symtbl)<<SYMBOL_NORMAL_SHIFT;
        }
        sname--;
      }
      return 0;
    }
    i -= sname->prev;
  } while (sname->prev > 0);
  return 0;
}