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
struct entry {void (* func ) (void*,void*) ;struct entry* prev; struct entry* next; void* data2; void* data1; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;
struct base {scalar_t__ registered; scalar_t__ wanted; struct entry* entries; struct entry* last; } ;

/* Variables and functions */
 struct base* calloc (int,int) ; 
 struct entry* malloc (int) ; 
 int /*<<< orphan*/  simple_hash2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static inline struct base *entry(struct base *base, const char *name, void *data1, void *data2, void (*func)(void *, void *)) {
  if(!base)
    base = calloc(1, sizeof(struct base));

  struct entry *e = malloc(sizeof(struct entry));
  e->name = strdup(name);
  e->hash = simple_hash2(e->name);
  e->data1 = data1;
  e->data2 = data2;
  e->func = func;
  e->prev = NULL;
  e->next = base->entries;

  if(base->entries) base->entries->prev = e;
  else base->last = e;

  base->entries = e;
  base->registered++;
  base->wanted = base->registered;

  return base;
}