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
typedef  scalar_t__ ut8 ;
typedef  int ut64 ;
struct TYPE_3__ {scalar_t__* data; } ;
typedef  int /*<<< orphan*/  RDebug ;

/* Variables and functions */
 int bAjusta ; 
 int bCapturaRegs ; 
 int /*<<< orphan*/  bochs_send_cmd (TYPE_1__*,char*,int) ; 
 TYPE_1__* desc ; 
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  isBochs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,...) ; 
 int r_num_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ripStop ; 
 scalar_t__* saveRegs ; 
 int strlen (scalar_t__*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static int r_debug_bochs_reg_read(RDebug *dbg, int type, ut8 *buf, int size) {
	char strReg[19];
	char regname[4];
	char strBase[19];
	char strLimit[19];
	int i = 0, pos = 0, lenRec = 0;
	ut64 val = 0, valRIP = 0; //, posRIP = 0;
	if (!isBochs (dbg)) {
		return 0;
	}

	//eprintf ("bochs_reg_read\n");
	if (bCapturaRegs == true) {
		bochs_send_cmd (desc, "regs", true);
		//r14: 00000000_00000000 r15: 00000000_00000000
		//rip: 00000000_0000e07b
		//eflags 0x00000046: id vip vif ac vm rf nt IOPL=0 of df if tf sf ZF af PF cf
		//<bochs:109>return -1;
		pos = 0x78;
		lenRec = strlen (desc->data);
		while (desc->data[i] != 0 && i < lenRec -4 ) {
			if ( (desc->data[i] == (ut8)'r' && desc->data[i + 3] == (ut8)':')) {
				strncpy (regname, &desc->data[i], 3);
				regname[3] = 0;
				strncpy (&strReg[2], &desc->data[i + 5], 8);
				strncpy (&strReg[10], &desc->data[i + 14], 8);
				strReg[0]='0';
				strReg[1]='x';
				strReg[18] = 0;
				i += 22;
				val = r_num_get (NULL, strReg);
				// eprintf("parseado %s = %s valx64 = %016"PFMT64x"\n", regname, strReg,val);
				memcpy (&buf[pos], &val, 8);
				// guardamos la posicion del rip y su valor para ajustarlo al obtener el CS
				if (!strncmp (regname, "rip", 3)) {
				// UNUSED	posRIP = pos;
					valRIP = val;
				}
				pos+= 8;

			} else {
				i++;
			}
		}

		bochs_send_cmd (desc, "info cpu", true);
		if (strstr (desc->data,"PC_32")) {
			bAjusta = true;
			//eprintf("[modo PC_32]\n");
		} else if (strstr (desc->data,"PC_80")) {
			bAjusta = false;
			//eprintf("[modo PC_80]\n");
		} else if (strstr (desc->data,"PC_64")) {
			bAjusta = false;
			//eprintf("[modo PC_64]\n");
		} else {
			eprintf ("[unknown mode]\n%s\n", desc->data);
		}
		/*
		   es:0x0000, dh=0x00009300, dl=0x0000ffff, valid=7
		   Data segment, base=0x00000000, limit=0x0000ffff, Read/Write, Accessed
		   cs:0xf000, dh=0xff0093ff, dl=0x0000ffff, valid=7
		   Data segment, base=0xffff0000, limit=0x0000ffff, Read/Write, Accessed
		   ss:0x0000, dh=0x00009300, dl=0x0000ffff, valid=7
		   Data segment, base=0x00000000, limit=0x0000ffff, Read/Write, Accessed
		   ds:0x0000, dh=0x00009300, dl=0x0000ffff, valid=7
		   Data segment, base=0x00000000, limit=0x0000ffff, Read/Write, Accessed
		   fs:0x0000, dh=0x00009300, dl=0x0000ffff, valid=7
		   Data segment, base=0x00000000, limit=0x0000ffff, Read/Write, Accessed
		   gs:0x0000, dh=0x00009300, dl=0x0000ffff, valid=7
		   Data segment, base=0x00000000, limit=0x0000ffff, Read/Write, Accessed
		   ldtr:0x0000, dh=0x00008200, dl=0x0000ffff, valid=1
		   tr:0x0000, dh=0x00008b00, dl=0x0000ffff, valid=1
		   gdtr:base=0x0000000000000000, limit=0xffff
		   idtr:base=0x0000000000000000, limit=0xffff
		*/
		bochs_send_cmd (desc, "sreg", true);

		pos = 0x38;
		char * s [] = { "es:0x", "cs:0x","ss:0x","ds:0x","fs:0x","gs:0x",0};
		const char *x;
		int n;
		for (n = 0; s[n] != 0; n++) {
			if ((x = strstr (desc->data,s[n]))) {
				strncpy (&strReg[0], x+3, 7);
				strReg[6] = 0;
				val = r_num_get (NULL, strReg);
				strncpy (regname, s[n], 2);
				regname[2] = 0;
				if ((x = strstr (x, "base="))) {
					strncpy (strBase, x + 5, 10);
					strBase[10] = 0;
					if ((x = strstr (x, "limit="))) {
						strncpy (strLimit, x + 6, 10);
						strLimit[10] = 0;
					}
				}
				//eprintf("%s localizado %s %04x base = %s limit = %s\n",regname,strReg,(WORD)val,strBase,strLimit);
				memcpy (&buf[pos], &val, 2);
				pos += 2;
				if (bAjusta) {
					if (!strncmp (regname,"cs",2)) {
						valRIP += (val*0x10); // desplazamos CS y lo añadimos a RIP
					//eprintf("%016"PFMT64x"\n",valRIP);
					}
				}
			}
		}
		// Cheat para evitar traducciones de direcciones
		if (ripStop != 0) {
			memcpy (&buf[0], &ripStop, 8);
		} else {
			memcpy (&buf[0], &valRIP, 8);	// guardamos el valor cs:ip en el registro virtual "vip"
		}
		//eprintf("guardando regs procesados%x\n",size);
		memcpy (saveRegs,buf,size);
		bCapturaRegs = false;
		//eprintf("bochs_reg_read\n");
	} else {
		memcpy (buf, saveRegs, size);
		//eprintf("[cache] bochs_reg_read\n");
	}
	return size;
}