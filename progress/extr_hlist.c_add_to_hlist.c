#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int value; struct TYPE_5__* prev; struct TYPE_5__* next; } ;
typedef  TYPE_1__ hlist ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 
 int max_hlist_size ; 

int add_to_hlist(hlist **begin, hlist **end, int size, int value) {
   int ret;

   if (*begin == NULL) {
       if ((*begin = malloc(sizeof(hlist))) == NULL)
           return 0;
       *end = *begin;
       (*begin)->next = NULL;
       (*begin)->prev = NULL;
       ret = 1;
   }
   else if (size == max_hlist_size) {
       hlist *tmp = (*end)->prev;
       tmp->next = NULL;
       (*end)->next = *begin;
       (*end)->prev = NULL;
       *begin = *end;
       *end = tmp;
       (*begin)->next->prev = *begin;
       ret = 0;
   }
   else {
       hlist *new = malloc(sizeof(hlist));
       if (!new)
           return 0;
       new->next = *begin;
       new->prev = NULL;
       *begin = new;
       (*begin)->next->prev = *begin;
       ret = 1;
   }
   (*begin)->value = value;
   return ret;
}