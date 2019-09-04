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
struct pnp_id {int dummy; } ;
struct pnp_dev {char* name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned char LARGE_TAG ; 
#define  LARGE_TAG_ANSISTR 130 
 int PNP_EISA_ID_MASK ; 
 int PNP_NAME_LEN ; 
#define  SMALL_TAG_COMPATDEVID 129 
#define  SMALL_TAG_END 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct pnp_id* pnp_add_id (struct pnp_dev*,char*) ; 
 int /*<<< orphan*/  pnp_eisa_id_to_string (int,char*) ; 
 int /*<<< orphan*/  strncpy (char*,unsigned char*,int) ; 

__attribute__((used)) static unsigned char *pnpbios_parse_compatible_ids(unsigned char *p,
						   unsigned char *end,
						   struct pnp_dev *dev)
{
	int len, tag;
	u32 eisa_id;
	char id[8];
	struct pnp_id *dev_id;

	if (!p)
		return NULL;

	while ((char *)p < (char *)end) {

		/* determine the type of tag */
		if (p[0] & LARGE_TAG) {	/* large tag */
			len = (p[2] << 8) | p[1];
			tag = p[0];
		} else {	/* small tag */
			len = p[0] & 0x07;
			tag = ((p[0] >> 3) & 0x0f);
		}

		switch (tag) {

		case LARGE_TAG_ANSISTR:
			strncpy(dev->name, p + 3,
				len >= PNP_NAME_LEN ? PNP_NAME_LEN - 2 : len);
			dev->name[len >=
				  PNP_NAME_LEN ? PNP_NAME_LEN - 1 : len] = '\0';
			break;

		case SMALL_TAG_COMPATDEVID:	/* compatible ID */
			if (len != 4)
				goto len_err;
			eisa_id = p[1] | p[2] << 8 | p[3] << 16 | p[4] << 24;
			pnp_eisa_id_to_string(eisa_id & PNP_EISA_ID_MASK, id);
			dev_id = pnp_add_id(dev, id);
			if (!dev_id)
				return NULL;
			break;

		case SMALL_TAG_END:
			p = p + 2;
			return (unsigned char *)p;
			break;

		default:	/* an unknown tag */
len_err:
			dev_err(&dev->dev, "unknown tag %#x length %d\n",
				tag, len);
			break;
		}

		/* continue to the next tag */
		if (p[0] & LARGE_TAG)
			p += len + 3;
		else
			p += len + 1;
	}

	dev_err(&dev->dev, "no end tag in resource structure\n");

	return NULL;
}