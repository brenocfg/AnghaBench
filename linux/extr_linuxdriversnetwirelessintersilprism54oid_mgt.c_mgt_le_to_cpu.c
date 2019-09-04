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
typedef  int u32 ;
struct obj_mlmeex {int id; int state; int code; int size; } ;
struct obj_mlme {int id; int state; int code; } ;
struct obj_frequencies {int nr; int* mhz; } ;
struct obj_buffer {int size; int addr; } ;
struct obj_bsslist {int nr; int /*<<< orphan*/ * bsslist; } ;
struct obj_bss {int age; int channel; int capinfo; int rates; int basic_rates; } ;
struct obj_attachment {int id; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  OID_TYPE_ADDR 139 
#define  OID_TYPE_ATTACH 138 
#define  OID_TYPE_BSS 137 
#define  OID_TYPE_BSSLIST 136 
#define  OID_TYPE_BUFFER 135 
#define  OID_TYPE_FREQUENCIES 134 
#define  OID_TYPE_KEY 133 
#define  OID_TYPE_MLME 132 
#define  OID_TYPE_MLMEEX 131 
#define  OID_TYPE_RAW 130 
#define  OID_TYPE_SSID 129 
#define  OID_TYPE_U32 128 
 void* le16_to_cpu (int) ; 
 void* le32_to_cpu (int) ; 

void
mgt_le_to_cpu(int type, void *data)
{
	switch (type) {
	case OID_TYPE_U32:
		*(u32 *) data = le32_to_cpu(*(u32 *) data);
		break;
	case OID_TYPE_BUFFER:{
			struct obj_buffer *buff = data;
			buff->size = le32_to_cpu(buff->size);
			buff->addr = le32_to_cpu(buff->addr);
			break;
		}
	case OID_TYPE_BSS:{
			struct obj_bss *bss = data;
			bss->age = le16_to_cpu(bss->age);
			bss->channel = le16_to_cpu(bss->channel);
			bss->capinfo = le16_to_cpu(bss->capinfo);
			bss->rates = le16_to_cpu(bss->rates);
			bss->basic_rates = le16_to_cpu(bss->basic_rates);
			break;
		}
	case OID_TYPE_BSSLIST:{
			struct obj_bsslist *list = data;
			int i;
			list->nr = le32_to_cpu(list->nr);
			for (i = 0; i < list->nr; i++)
				mgt_le_to_cpu(OID_TYPE_BSS, &list->bsslist[i]);
			break;
		}
	case OID_TYPE_FREQUENCIES:{
			struct obj_frequencies *freq = data;
			int i;
			freq->nr = le16_to_cpu(freq->nr);
			for (i = 0; i < freq->nr; i++)
				freq->mhz[i] = le16_to_cpu(freq->mhz[i]);
			break;
		}
	case OID_TYPE_MLME:{
			struct obj_mlme *mlme = data;
			mlme->id = le16_to_cpu(mlme->id);
			mlme->state = le16_to_cpu(mlme->state);
			mlme->code = le16_to_cpu(mlme->code);
			break;
		}
	case OID_TYPE_MLMEEX:{
			struct obj_mlmeex *mlme = data;
			mlme->id = le16_to_cpu(mlme->id);
			mlme->state = le16_to_cpu(mlme->state);
			mlme->code = le16_to_cpu(mlme->code);
			mlme->size = le16_to_cpu(mlme->size);
			break;
		}
	case OID_TYPE_ATTACH:{
			struct obj_attachment *attach = data;
			attach->id = le16_to_cpu(attach->id);
			attach->size = le16_to_cpu(attach->size);
			break;
	}
	case OID_TYPE_SSID:
	case OID_TYPE_KEY:
	case OID_TYPE_ADDR:
	case OID_TYPE_RAW:
		break;
	default:
		BUG();
	}
}