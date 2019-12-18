#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int blockSizeID; } ;
typedef  TYPE_1__ LZ4F_frameInfo_t ;

/* Variables and functions */
#define  LZ4F_default 132 
#define  LZ4F_max1MB 131 
#define  LZ4F_max256KB 130 
#define  LZ4F_max4MB 129 
#define  LZ4F_max64KB 128 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static size_t get_block_size(const LZ4F_frameInfo_t* info) {
    switch (info->blockSizeID) {
        case LZ4F_default:
        case LZ4F_max64KB:  return 1 << 16;
        case LZ4F_max256KB: return 1 << 18;
        case LZ4F_max1MB:   return 1 << 20;
        case LZ4F_max4MB:   return 1 << 22;
        default:
            printf("Impossible with expected frame specification (<=v1.6.1)\n");
            exit(1);
    }
}