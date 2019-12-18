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
struct TYPE_4__ {int e_type; } ;
struct TYPE_5__ {TYPE_1__ ehdr; } ;
typedef  TYPE_2__ ELFOBJ ;

/* Variables and functions */
#define  ET_DYN 129 
#define  ET_EXEC 128 

__attribute__((used)) static bool isExecutable(ELFOBJ *bin) {
	switch (bin->ehdr.e_type) {
	case ET_EXEC: return true;
	case ET_DYN:  return true;
	}
	return false;
}