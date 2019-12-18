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

/* Variables and functions */

__attribute__((used)) static void QuickSort(void *list[], int low, int high,
                      int (*Comp)(const void *, const void *))
{
   int     flag = 1, i, j;
   void    *key, *temp;

   if(low < high) {
      i = low;
      j = high + 1;

      key = list[ low ];

      while(flag) {
         i++;
         while(Comp(list[i], key) < 0)
            i++;

         j--;
         while(Comp(list[j], key) > 0)
            j--;

         if(i < j) {
            temp = list[i];
            list[i] = list[j];
            list[j] = temp;
         }
         else  flag = 0;
      }

      temp = list[low];
      list[low] = list[j];
      list[j] = temp;

      QuickSort(list, low, j-1, Comp);
      QuickSort(list, j+1, high, Comp);
   }
}