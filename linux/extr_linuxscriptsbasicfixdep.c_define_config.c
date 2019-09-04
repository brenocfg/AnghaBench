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
struct item {int len; unsigned int hash; struct item* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int HASHSZ ; 
 int /*<<< orphan*/  exit (int) ; 
 struct item** hashtab ; 
 struct item* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void define_config(const char *name, int len, unsigned int hash)
{
	struct item *aux = malloc(sizeof(*aux) + len);

	if (!aux) {
		perror("fixdep:malloc");
		exit(1);
	}
	memcpy(aux->name, name, len);
	aux->len = len;
	aux->hash = hash;
	aux->next = hashtab[hash % HASHSZ];
	hashtab[hash % HASHSZ] = aux;
}