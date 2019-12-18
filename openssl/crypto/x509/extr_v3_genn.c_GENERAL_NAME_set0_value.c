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
struct TYPE_4__ {void* rid; void* ip; void* dirn; void* ia5; void* otherName; void* other; } ;
struct TYPE_5__ {int type; TYPE_1__ d; } ;
typedef  TYPE_2__ GENERAL_NAME ;

/* Variables and functions */
#define  GEN_DIRNAME 136 
#define  GEN_DNS 135 
#define  GEN_EDIPARTY 134 
#define  GEN_EMAIL 133 
#define  GEN_IPADD 132 
#define  GEN_OTHERNAME 131 
#define  GEN_RID 130 
#define  GEN_URI 129 
#define  GEN_X400 128 

void GENERAL_NAME_set0_value(GENERAL_NAME *a, int type, void *value)
{
    switch (type) {
    case GEN_X400:
    case GEN_EDIPARTY:
        a->d.other = value;
        break;

    case GEN_OTHERNAME:
        a->d.otherName = value;
        break;

    case GEN_EMAIL:
    case GEN_DNS:
    case GEN_URI:
        a->d.ia5 = value;
        break;

    case GEN_DIRNAME:
        a->d.dirn = value;
        break;

    case GEN_IPADD:
        a->d.ip = value;
        break;

    case GEN_RID:
        a->d.rid = value;
        break;
    }
    a->type = type;
}