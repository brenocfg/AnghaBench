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
typedef  int D3DVSDE_REGISTER ;

/* Variables and functions */
#define  D3DVSDE_BLENDINDICES 144 
#define  D3DVSDE_BLENDWEIGHT 143 
#define  D3DVSDE_DIFFUSE 142 
#define  D3DVSDE_NORMAL 141 
#define  D3DVSDE_NORMAL2 140 
#define  D3DVSDE_POSITION 139 
#define  D3DVSDE_POSITION2 138 
#define  D3DVSDE_PSIZE 137 
#define  D3DVSDE_SPECULAR 136 
#define  D3DVSDE_TEXCOORD0 135 
#define  D3DVSDE_TEXCOORD1 134 
#define  D3DVSDE_TEXCOORD2 133 
#define  D3DVSDE_TEXCOORD3 132 
#define  D3DVSDE_TEXCOORD4 131 
#define  D3DVSDE_TEXCOORD5 130 
#define  D3DVSDE_TEXCOORD6 129 
#define  D3DVSDE_TEXCOORD7 128 
 int /*<<< orphan*/  FIXME (char*,int) ; 

__attribute__((used)) static const char *debug_d3dvsde_register(D3DVSDE_REGISTER d3dvsde_register)
{
    switch (d3dvsde_register)
    {
#define D3DVSDE_REGISTER_TO_STR(u) case u: return #u
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_POSITION);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_BLENDWEIGHT);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_BLENDINDICES);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_NORMAL);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_PSIZE);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_DIFFUSE);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_SPECULAR);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_TEXCOORD0);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_TEXCOORD1);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_TEXCOORD2);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_TEXCOORD3);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_TEXCOORD4);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_TEXCOORD5);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_TEXCOORD6);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_TEXCOORD7);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_POSITION2);
        D3DVSDE_REGISTER_TO_STR(D3DVSDE_NORMAL2);
#undef D3DVSDE_REGISTER_TO_STR
        default:
            FIXME("Unrecognized D3DVSDE_REGISTER %#x\n", d3dvsde_register);
            return "unrecognized";
    }
}