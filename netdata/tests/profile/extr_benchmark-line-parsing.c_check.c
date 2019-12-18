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
typedef  scalar_t__ uint32_t ;
struct entry {char const* name; int found; scalar_t__ hash; struct entry* next; struct entry* prev; int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct base {scalar_t__ found; scalar_t__ registered; struct entry* entries; struct entry* last; } ;

/* Variables and functions */
 struct entry* calloc (int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ simple_hash2 (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 char const* strdup (char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int check(struct base *base, const char *s) {
  uint32_t hash = simple_hash2(s);

  if(likely(!strcmp(s, base->last->name))) {
    base->last->found = 1;
    base->found++;
    if(base->last->func) base->last->func(base->last->data1, base->last->data2);
    base->last = base->last->next;

    if(!base->last)
      base->last = base->entries;

    if(base->found == base->registered)
      return 1;

    return 0;
  }

  // find it
  struct entry *e;
  for(e = base->entries; e ; e = e->next)
    if(e->hash == hash && !strcmp(e->name, s))
      break;

  if(e == base->last) {
    printf("ERROR\n");
    exit(1);
  }

  if(e) {
    // found

    // run it
    if(e->func) e->func(e->data1, e->data2);

    // unlink it
    if(e->next) e->next->prev = e->prev;
    if(e->prev) e->prev->next = e->next;

    if(base->entries == e)
      base->entries = e->next;
  }
  else {
    // not found

    // create it
    e = calloc(1, sizeof(struct entry));
    e->name = strdup(s);
    e->hash = hash;
  }

  // link it here
  e->next = base->last;
  if(base->last) {
    e->prev = base->last->prev;
    base->last->prev = e;

    if(base->entries == base->last)
      base->entries = e;
  }
  else
    e->prev = NULL;

  if(e->prev)
    e->prev->next = e;

  base->last = e->next;
  if(!base->last)
    base->last = base->entries;

  e->found = 1;
  base->found++;

  if(base->found == base->registered)
    return 1;

  printf("relinked '%s' after '%s' and before '%s': ", e->name, e->prev?e->prev->name:"NONE", e->next?e->next->name:"NONE");
  for(e = base->entries; e ; e = e->next) printf("%s ", e->name);
  printf("\n");

  return 0;
}