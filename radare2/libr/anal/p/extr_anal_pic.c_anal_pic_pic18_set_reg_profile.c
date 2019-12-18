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
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ RAnal ;

/* Variables and functions */
 int r_reg_set_profile_string (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int anal_pic_pic18_set_reg_profile(RAnal *esil) {
	const char *p;
	p =
		"#pc lives in nowhere actually"
		"=PC	pc\n"
		"=SP	tos\n"
		"gpr	pc	.32	0	0\n"
		"gpr	pcl	.8	0	0\n"
		"gpr	pclath	.8	1	0\n"
		"gpr	pclatu	.8	2	0\n"
		"#bsr max is 0b111\n"
		"gpr	bsr	.8	4	0\n"
		"#tos doesn't exist\n"
		"#general rule of thumb any register of size >8 bits has no existence\n"
		"gpr	tos	.32	5	0\n"
		"gpr	tosl	.8	5	0\n"
		"gpr	tosh	.8	6	0\n"
		"gpr	tosu	.8	7	0\n"

		"gpr	indf0	.16	9	0\n"
		"gpr	fsr0	.12	9	0\n"
		"gpr	fsr0l	.8	9	0\n"
		"gpr	fsr0h	.8	10	0\n"
		"gpr	indf1	.16	11	0\n"
		"gpr	fsr1	.12	11	0\n"
		"gpr	fsr1l	.8	11	0\n"
		"gpr	fsr1h	.8	12	0\n"
		"gpr	indf2	.16	13	0\n"
		"gpr	fsr2	.12	13	0\n"
		"gpr	frs2l	.8	13	0\n"
		"gpr	fsr2h	.8	14	0\n"
		"gpr	tblptr	.22	15	0\n"
		"gpr	tblptrl	.8	15	0\n"
		"gpr	tblptrh	.8	16	0\n"
		"gpr	tblptru	.8	17	0\n"
		"gpr	rcon	.8	18	0\n"
		"gpr	memcon	.8	19	0\n"
		"gpr	intcon	.8	20	0\n"
		"gpr	intcon2	.8	21	0\n"
		"gpr	intcon3	.8	22	0\n"
		"gpr	pie1	.8	23	0\n"
		"gpr	porta	.7	29	0\n"
		"gpr	trisa	.8	30	0\n"
		"gpr	portb	.8	33	0\n"
		"gpr	tisb	.8	34	0\n"
		"gpr	latb	.8	35	0\n"
		"gpr	portc	.8	36	0\n"
		"gpr	trisc	.8	37	0\n"
		"gpr	latc	.8	38	0\n"
		"gpr	portd	.8	39	0\n"
		"gpr	trisd	.8	40	0\n"
		"gpr	latd	.8	41	0\n"
		"gpr	pspcon	.8	42	0\n"
		"gpr	porte	.8	43	0\n"
		"gpr	trise	.8	44	0\n"
		"gpr	late	.8	45	0\n"
		"gpr	t0con	.8	46	0\n"
		"gpr	t1con	.8	47	0\n"
		"gpr	t2con	.8	48	0\n"
		"gpr	tmr1h	.8	50	0\n"
		"gpr	tmr0h	.8	51	0\n"
		"gpr	tmr1l	.8	52	0\n"
		"gpr	tmr2	.8	53	0\n"
		"gpr	pr2	.8	54	0\n"
		"gpr	ccpr1h	.8	55	0\n"
		"gpr	postinc2 .8	56	0\n"
		"gpr	ccpr1l	.8	57	0\n"
		"gpr	postdec2 .8	58	0\n"
		"gpr	ccp1con	.8	59	0\n"
		"gpr	preinc2	.8	60	0\n"
		"gpr	ccpr2h	.8	61	0\n"
		"gpr	plusw2	.8	62	0\n"
		"gpr	ccpr2l	.8	63	0\n"
		"gpr	ccp2con	.8	64	0\n"
		"gpr	status	.8	65	0\n"
		"flg	c	.1	.520	0\n"
		"flg	dc	.1	.521	0\n"
		"flg	z	.1	.522	0\n"
		"flg	ov	.1	.523	0\n"
		"flg	n	.1	.524	0\n"
		"gpr	prod	.16	66	0\n"
		"gpr	prodl	.8	66	0\n"
		"gpr	prodh	.8	67	0\n"
		"gpr	osccon	.8	68	0\n"
		"gpr	tmr3h	.8	69	0\n"
		"gpr	lvdcon	.8	70	0\n"
		"gpr	tmr3l	.8	71	0\n"
		"gpr	wdtcon	.8	72	0\n"
		"gpr	t3con	.8	73	0\n"
		"gpr	spbrg	.8	74	0\n"
		"gpr	postinc0 .8	75	0\n"
		"gpr	rcreg	.8	76	0\n"
		"gpr	postdec0 .8	77	0\n"
		"gpr	txreg	.8	78	0\n"
		"gpr	preinc0	.8	79	0\n"
		"gpr	txsta	.8	80	0\n"
		"gpr	plusw0	.8	81	0\n"
		"gpr	rcsta	.8	82	0\n"
		"gpr	sspbuf	.8	83	0\n"
		"gpr	wreg	.8	84	0\n"
		"gpr	sspadd	.8	85	0\n"
		"gpr	sspstat	.8	86	0\n"
		"gpr	postinc1 .8	87	0\n"
		"gpr	sspcon1	.8	88	0\n"
		"gpr	postdec1 .8	89	0\n"
		"gpr	sspcon2	.8	90	0\n"
		"gpr	preinc1	.8	91	0\n"
		"gpr	adresh	.8	92	0\n"
		"gpr	plusw1	.8	93	0\n"
		"gpr	adresl	.8	94	0\n"
		"gpr	adcon0	.8	95	0\n"
		"#stkprt max is 0b11111\n"
		"gpr	stkptr	.8	96	0\n"
		"gpr	tablat	.8	14	0\n";

	return r_reg_set_profile_string (esil->reg, p);
}