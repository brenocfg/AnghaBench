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
struct QTMmodelsym {int sym; int cumfreq; } ;
struct QTMmodel {int shiftsleft; int entries; int* tabloc; struct QTMmodelsym* syms; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static void QTMfdi_initmodel(struct QTMmodel *m, struct QTMmodelsym *sym, int n, int s) {
  int i;
  m->shiftsleft = 4;
  m->entries    = n;
  m->syms       = sym;
  memset(m->tabloc, 0xFF, sizeof(m->tabloc)); /* clear out look-up table */
  for (i = 0; i < n; i++) {
    m->tabloc[i+s]     = i;   /* set up a look-up entry for symbol */
    m->syms[i].sym     = i+s; /* actual symbol */
    m->syms[i].cumfreq = n-i; /* current frequency of that symbol */
  }
  m->syms[n].cumfreq = 0;
}