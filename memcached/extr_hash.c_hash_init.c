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
typedef  enum hashfunc_type { ____Placeholder_hashfunc_type } hashfunc_type ;
struct TYPE_2__ {char* hash_algorithm; } ;

/* Variables and functions */
#define  JENKINS_HASH 129 
#define  MURMUR3_HASH 128 
 int /*<<< orphan*/  MurmurHash3_x86_32 ; 
 int /*<<< orphan*/  hash ; 
 int /*<<< orphan*/  jenkins_hash ; 
 TYPE_1__ settings ; 

int hash_init(enum hashfunc_type type) {
    switch(type) {
        case JENKINS_HASH:
            hash = jenkins_hash;
            settings.hash_algorithm = "jenkins";
            break;
        case MURMUR3_HASH:
            hash = MurmurHash3_x86_32;
            settings.hash_algorithm = "murmur3";
            break;
        default:
            return -1;
    }
    return 0;
}