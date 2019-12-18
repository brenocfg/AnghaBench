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
struct TYPE_2__ {int vendor_id; } ;
struct hda_codec {TYPE_1__ core; } ;

/* Variables and functions */
 int alc_get_coef0 (struct hda_codec*) ; 
 int /*<<< orphan*/  alc_update_coef_idx (struct hda_codec*,int,int,int) ; 

__attribute__((used)) static void alc_fill_eapd_coef(struct hda_codec *codec)
{
	int coef;

	coef = alc_get_coef0(codec);

	switch (codec->core.vendor_id) {
	case 0x10ec0262:
		alc_update_coef_idx(codec, 0x7, 0, 1<<5);
		break;
	case 0x10ec0267:
	case 0x10ec0268:
		alc_update_coef_idx(codec, 0x7, 0, 1<<13);
		break;
	case 0x10ec0269:
		if ((coef & 0x00f0) == 0x0010)
			alc_update_coef_idx(codec, 0xd, 0, 1<<14);
		if ((coef & 0x00f0) == 0x0020)
			alc_update_coef_idx(codec, 0x4, 1<<15, 0);
		if ((coef & 0x00f0) == 0x0030)
			alc_update_coef_idx(codec, 0x10, 1<<9, 0);
		break;
	case 0x10ec0280:
	case 0x10ec0284:
	case 0x10ec0290:
	case 0x10ec0292:
		alc_update_coef_idx(codec, 0x4, 1<<15, 0);
		break;
	case 0x10ec0225:
	case 0x10ec0295:
	case 0x10ec0299:
		alc_update_coef_idx(codec, 0x67, 0xf000, 0x3000);
		/* fallthrough */
	case 0x10ec0215:
	case 0x10ec0233:
	case 0x10ec0235:
	case 0x10ec0236:
	case 0x10ec0255:
	case 0x10ec0256:
	case 0x10ec0257:
	case 0x10ec0282:
	case 0x10ec0283:
	case 0x10ec0286:
	case 0x10ec0288:
	case 0x10ec0285:
	case 0x10ec0298:
	case 0x10ec0289:
	case 0x10ec0300:
		alc_update_coef_idx(codec, 0x10, 1<<9, 0);
		break;
	case 0x10ec0275:
		alc_update_coef_idx(codec, 0xe, 0, 1<<0);
		break;
	case 0x10ec0293:
		alc_update_coef_idx(codec, 0xa, 1<<13, 0);
		break;
	case 0x10ec0234:
	case 0x10ec0274:
	case 0x10ec0294:
	case 0x10ec0700:
	case 0x10ec0701:
	case 0x10ec0703:
	case 0x10ec0711:
		alc_update_coef_idx(codec, 0x10, 1<<15, 0);
		break;
	case 0x10ec0662:
		if ((coef & 0x00f0) == 0x0030)
			alc_update_coef_idx(codec, 0x4, 1<<10, 0); /* EAPD Ctrl */
		break;
	case 0x10ec0272:
	case 0x10ec0273:
	case 0x10ec0663:
	case 0x10ec0665:
	case 0x10ec0670:
	case 0x10ec0671:
	case 0x10ec0672:
		alc_update_coef_idx(codec, 0xd, 0, 1<<14); /* EAPD Ctrl */
		break;
	case 0x10ec0623:
		alc_update_coef_idx(codec, 0x19, 1<<13, 0);
		break;
	case 0x10ec0668:
		alc_update_coef_idx(codec, 0x7, 3<<13, 0);
		break;
	case 0x10ec0867:
		alc_update_coef_idx(codec, 0x4, 1<<10, 0);
		break;
	case 0x10ec0888:
		if ((coef & 0x00f0) == 0x0020 || (coef & 0x00f0) == 0x0030)
			alc_update_coef_idx(codec, 0x7, 1<<5, 0);
		break;
	case 0x10ec0892:
		alc_update_coef_idx(codec, 0x7, 1<<5, 0);
		break;
	case 0x10ec0899:
	case 0x10ec0900:
	case 0x10ec1168:
	case 0x10ec1220:
		alc_update_coef_idx(codec, 0x7, 1<<1, 0);
		break;
	}
}